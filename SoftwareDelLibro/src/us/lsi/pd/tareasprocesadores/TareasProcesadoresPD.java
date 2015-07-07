package us.lsi.pd.tareasprocesadores;

import java.util.List;
import java.util.Map;
import java.util.Comparator;

import us.lsi.common.Lists2;
import us.lsi.pd.AlgoritmoPD.Sp;
import us.lsi.pd.ProblemaPD;

import java.util.stream.Collectors;
import java.util.stream.IntStream;

import com.google.common.base.Preconditions;
import com.google.common.collect.Lists;
import com.google.common.collect.Maps;


public class TareasProcesadoresPD implements ProblemaPD<Map<Integer,List<Tarea>>, Integer> {

	public static Integer numeroDeProcesadores;
	public static Integer numeroDeTareas;
	public static List<Double> duracionDeTareas;
	public static TareasProcesadoresPD inicial;

	
	public static TareasProcesadoresPD create(String fichero, Integer np) {
		Tarea.leeTareas(fichero);
		numeroDeProcesadores = np;
		numeroDeTareas = Tarea.tareas.size();
		duracionDeTareas = Tarea.tareas.stream().map(t->t.getDuracion()).collect(Collectors.toList());
		List<Double> cargaProcesadoresAcumulada = ListDoubleHelper.getZerolist(numeroDeProcesadores);
		inicial = new TareasProcesadoresPD(0, cargaProcesadoresAcumulada);
		return inicial;
	}
	
	public static TareasProcesadoresPD create(int index, List<Double> cargaProcesadoresAcumulada) {
		return new TareasProcesadoresPD(index, cargaProcesadoresAcumulada);		
	}

	private int index;
	private List<Double> cargaProcesadoresAcumulada; //tp
	private Double tiempoAcumulado; // t. Calculado hacia abajo
	private Sol solP = null; // Solución parcial del problema tras la llamada al método seleccionaAlternativa
	
//	private Double  tiempoSolucion = Double.MAX_VALUE; // tiempo de la solución del problema. 
					                                   // Calculado hacia arriba o el valor por defecto
	
	private TareasProcesadoresPD(int index, List<Double> cargaProcesadoresAcumulada) {
		super();
		this.index = index;
		this.cargaProcesadoresAcumulada = cargaProcesadoresAcumulada;
		this.tiempoAcumulado = this.cargaProcesadoresAcumulada.stream().max(Comparator.naturalOrder()).get();
	}

	@Override
	public ProblemaPD.Tipo getTipo() {
		return Tipo.Min;
	}

	@Override
	public int size() {
		return numeroDeTareas - index;
	}

	@Override
	public boolean esCasoBase() {
		return index == numeroDeTareas;
	}

	@Override
	public Sp<Integer> getSolucionCasoBase() {	
		solP = Sol.create(0,Lists2.nCopias(numeroDeProcesadores, 0.));
		return solP;
	}

	@Override 
	public Sp<Integer> seleccionaAlternativa(List<Sp<Integer>> ls) {
		solP = (Sol) ls.stream().min(Comparator.naturalOrder()).orElse(null);
		return solP;
	}
	
	@Override
	public ProblemaPD<Map<Integer, List<Tarea>>, Integer> getSubProblema(Integer a, int np) {
		List<Double> duracion = actualizaCarga(index,a,cargaProcesadoresAcumulada);
		TareasProcesadoresPD p = TareasProcesadoresPD.create(index+1, duracion);
		return p;
	}

	@Override
	public Sp<Integer> combinaSolucionesParciales(Integer a, List<Sp<Integer>> ls) {
		List<Double> carga = Lists.newArrayList(Sol.asSol(ls.get(0)).carga);
		carga = actualizaCarga(index, a, carga);
		Sol s = Sol.create(a, carga);
		return s;
	}

	@Override
	public List<Integer> getAlternativas() {
		return IntStream.range(0,numeroDeProcesadores).boxed().collect(Collectors.toList());
	}

	@Override
	public int getNumeroSubProblemas(Integer a) {		
		return 1;
	}

	@Override
	public Map<Integer,List<Tarea>> getSolucionReconstruida(Sp<Integer> sp) {
		return Maps.newHashMap();
	}

	@Override
	public Map<Integer, List<Tarea>> getSolucionReconstruida(Sp<Integer> sp, List<Map<Integer, List<Tarea>>> ls) {
		Map<Integer,List<Tarea>>  m = Maps.newHashMap(ls.get(0));
		List<Tarea>  ts;
		if(m.containsKey(sp.alternativa)){
			ts = m.get(sp.alternativa);
		} else {
			ts = Lists.newArrayList();
			m.put(sp.alternativa, ts);
		}
		ts.add(Tarea.tareas.get(index));
		return m;
	}

	@Override
	public Double getObjetivoEstimado(Integer a) {
		return tiempoAcumulado;
	}

	@Override
	public Double getObjetivo() {
		if (solP!=null) {
			return tiempoAcumulado + solP.propiedad;
		}else{
			return tiempoAcumulado +Double.MAX_VALUE;
		}
	}
	
	private static List<Double> actualizaCarga(int t, int p, List<Double> carga) {
		List<Double>  ls  = Lists.newArrayList(carga);
		ls.set(p, ls.get(p)+duracionDeTareas.get(t));
		return ls;
	}

	
	@Override
	public int hashCode() {
		final int prime = 31;
		int result = 1;
		result = prime
				* result
				+ ((cargaProcesadoresAcumulada == null) ? 0
						: cargaProcesadoresAcumulada.hashCode());
		result = prime * result + index;
		return result;
	}

	@Override
	public boolean equals(Object obj) {
		if (this == obj)
			return true;
		if (obj == null)
			return false;
		if (!(obj instanceof TareasProcesadoresPD))
			return false;
		TareasProcesadoresPD other = (TareasProcesadoresPD) obj;
		if (cargaProcesadoresAcumulada == null) {
			if (other.cargaProcesadoresAcumulada != null)
				return false;
		} else if (!cargaProcesadoresAcumulada
				.equals(other.cargaProcesadoresAcumulada))
			return false;
		if (index != other.index)
			return false;
		return true;
	}

	@Override
	public String toString() {
		return "(" + index
				+ "," + cargaProcesadoresAcumulada
				+ ")";
	}
	
	public static class Sol extends Sp<Integer> {

		public List<Double> carga;
		
		public static Sol asSol(Sp<Integer> s){
			return (Sol)s;
		}
		
		public static Sol create(Integer alternativa, List<Double> carga) {
			Double t = carga.stream().max(Comparator.naturalOrder()).get();
			return new Sol(alternativa, t, carga);
		}
		
		private Sol(Integer alternativa, Double propiedad, List<Double> info) {
			super(alternativa, propiedad);
			this.carga = info;
		}		
	}
	
	public static class ListDoubleHelper {
		
		public static List<Double> addInPosition(List<Double> ls, int pos, Double q){
			List<Double> r = Lists.newArrayList(ls);
			Double qOld = r.get(pos);
			r.set(pos, qOld+q);
			return r;
		}
		
		public static Double maxList(List<Double> ls){
			return ls.stream().max(Comparator.naturalOrder()).orElse(null);
		}
		
		public static List<Double> addList(List<Double> ls1, List<Double> ls2){
			Preconditions.checkArgument(ls1.size() == ls2.size());
			List<Double> r = Lists.newArrayList();
			for(int i =0;i<ls1.size();i++){
				r.add(ls1.get(i)+ls2.get(i));
			}
			return r;
		}
		
		public static List<Double> getZerolist(int dim){
			Preconditions.checkArgument(dim>=0);
			List<Double> r = Lists.newArrayList();
			for(int i =0;i<dim;i++){
				r.add(0.);
			}
			return r;
		}
	}
}
